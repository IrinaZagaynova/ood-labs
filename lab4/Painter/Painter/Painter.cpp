#include "Painter.h"

void CPainter::DrawPicture(CPictureDraft& draft, ICanvas& canvas) const
{
	for (auto iter = draft.begin(); iter != draft.end(); iter++)
	{
		iter->Draw(canvas);
	}
}
