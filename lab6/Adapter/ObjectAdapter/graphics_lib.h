#pragma once
#include <iostream>
#include <iomanip>

using namespace std;

namespace graphics_lib
{
    // ����� ��� ���������
    class ICanvas
    {
    public:
        // ��������� ����� � ������� 0xRRGGBB
        virtual void SetColor(uint32_t rgbColor) = 0;
        virtual void MoveTo(int x, int y) = 0;
        virtual void LineTo(int x, int y) = 0;
        virtual ~ICanvas() = default;
    };

    // ���������� ������ ��� ���������
    class CCanvas : public ICanvas
    {
    public:
        void SetColor(uint32_t rgbColor) override
        {
            cout << "SetColor (#" << setfill('0') << setw(6) << std::hex << rgbColor << ")" << std::dec << endl;
        }
        void MoveTo(int x, int y) override
        {
            cout << "MoveTo (" << x << ", " << y << ")" << endl;
        }
        void LineTo(int x, int y) override
        {
            cout << "LineTo (" << x << ", " << y << ")" << endl;
        }
    };
}

