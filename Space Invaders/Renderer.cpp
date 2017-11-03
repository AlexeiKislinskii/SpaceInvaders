#include "Renderer.h"
#include "Objects\Maps\BaseMap.h"
#include "Game.h"
#include <Windows.h>
#include <string>
#include <iostream>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>

CRenderer::CRenderer() :
  IUpdateable(FAST_UPDATE),
  m_ScreenWidth(0),
  m_ScreenHeight(0),
  m_LastRenderMap(),
  m_CurrentRenderMap(),
  m_ConsoleHandle(nullptr),
  m_CameraYPosition(0)
{
}

void CRenderer::Init()
{
  CONSOLE_CURSOR_INFO CursorInfo;
  CONSOLE_SCREEN_BUFFER_INFO CursorBufferInfo;

  m_ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

  GetConsoleScreenBufferInfo(m_ConsoleHandle, &CursorBufferInfo);
  m_ScreenWidth = (size_t)(CursorBufferInfo.srWindow.Right - CursorBufferInfo.srWindow.Left + 1);
  m_ScreenHeight = (size_t)(CursorBufferInfo.srWindow.Bottom - CursorBufferInfo.srWindow.Top + 1);

  SetConsoleScreenBufferSize(m_ConsoleHandle, COORD{ (short)m_ScreenWidth, (short)m_ScreenHeight - 1 });

  GetConsoleCursorInfo(m_ConsoleHandle, &CursorInfo);
  CursorInfo.bVisible = false;
  SetConsoleCursorInfo(m_ConsoleHandle, &CursorInfo);

  m_CurrentRenderMap = m_LastRenderMap = std::vector<std::string>(m_ScreenHeight);

  for (size_t i = 0; i < m_ScreenHeight; i++)
    m_CurrentRenderMap[i] = m_LastRenderMap[i] = std::string(m_ScreenWidth, ' ');
}

void CRenderer::Update(double time)
{
  auto & Map = MapManager.GetCurrentMap();
  auto & Objects = Map.GetAllObjects();
  for (IBaseObject * Obj : Objects)
    Add(*Obj);

  UpdateHUD();
  Output();

  for (auto & line : m_CurrentRenderMap)
    for (auto & symbol : line)
      symbol = ' ';

  if (m_CameraYPosition + m_ScreenWidth >= Map.GetWidth())
    ShipManager.StopAllShips();
}

void CRenderer::Add(IBaseObject & Object)
{
  const CRect & Bounds = Object.GetBounds();

  size_t EndOfscreenPos = m_CameraYPosition + m_ScreenWidth;

  if (Bounds.pos.y > (int)EndOfscreenPos ||
      Bounds.pos.y + (int)Bounds.width < m_CameraYPosition)
    return;

  const std::vector<std::string> & Texture = Object.GetTexture();

  size_t MaxX = min(m_ScreenHeight, Bounds.pos.x + Bounds.height);
  size_t MinY = max(Bounds.pos.y, m_CameraYPosition);
  size_t MaxY = min(EndOfscreenPos, Bounds.pos.y + Bounds.width);

  bool IsVisible = false;

  for (size_t i = Bounds.pos.x, TextureX = 0; i < MaxX; i++, TextureX++)
  {
    for (size_t j = MinY, TextureY = MinY - Bounds.pos.y; j < MaxY; j++, TextureY++)
    {
      auto Symbol = Texture[TextureX][TextureY];

      if (Symbol == ' ')
        continue;

      IsVisible = true;

      m_CurrentRenderMap[i][j - m_CameraYPosition] = Symbol == '@' ? ' ' : Symbol;
    }
  }

  Object.SetIsOnScreen(IsVisible);
}

const CRect CRenderer::GetScreenRect() const
{
  return CRect(CVector2i(0, m_CameraYPosition), m_ScreenHeight, m_ScreenWidth);
}

void CRenderer::SetRenderPosition(int Position)
{
  m_CameraYPosition = Position;
}

void CRenderer::Clear()
{
  for (size_t i = 0; i < m_ScreenHeight; i++)
    for (size_t j = 0; j < m_ScreenWidth; j++)
    {
      SetConsoleCursorPosition(m_ConsoleHandle, COORD{ (short)j, (short)i });

      std::cout << ' ';
    }

  for (auto str : m_LastRenderMap)
    str.clear();
}

void Pro(size_t from, size_t to)
{}

void CRenderer::Output()
{
  for (size_t i = 0; i < m_ScreenHeight; i++)
    for (size_t j = 0; j < m_ScreenWidth; j++)
    {
      if (m_LastRenderMap[i][j] == m_CurrentRenderMap[i][j])
        continue;

      SetConsoleCursorPosition(m_ConsoleHandle, COORD{ (short)j, (short)i });

      std::cout << m_CurrentRenderMap[i][j];

      m_LastRenderMap[i][j] = m_CurrentRenderMap[i][j];
    }

  SetConsoleCursorPosition(m_ConsoleHandle, COORD{ 0, 0 });
}

void CRenderer::UpdateHUD()
{
  size_t Lifes = PlayerProfile.GetLifesCount();
  size_t Score = PlayerProfile.GetScore();
  std::string FirstLine = 
    "|Lifes: " + 
    std::to_string(Lifes % 10) + 
    " Score: " +
    std::to_string(Score / 1000 % 10) +
    std::to_string(Score / 100 % 10) +
    std::to_string(Score / 10 % 10) +
    std::to_string(Score % 10) +
    "|";

  std::string SecondLine = "";
  for (size_t i = 0; i < FirstLine.length(); i++)
    SecondLine += (i == 0 || i == FirstLine.length() - 1) ? '+' : '-';

  size_t GameInfoStart = (m_ScreenWidth / 2) - (FirstLine.length() / 2);

  m_CurrentRenderMap[0].replace(GameInfoStart, FirstLine.length(), FirstLine);
  m_CurrentRenderMap[1].replace(GameInfoStart, SecondLine.length(), SecondLine);
}
