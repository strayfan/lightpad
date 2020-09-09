
#ifndef LIGHTPAD_PIECETABLE_H
#define LIGHTPAD_PIECETABLE_H

#include "textbuffer.h"

namespace lightpad
{
	namespace core
	{
		class PieceTable
		{
			typedef unsigned short UTF16;
			typedef TextBuffer<UTF16> TextBuffer;
		public:
			PieceTable();
			~PieceTable();

		private:
			TextBuffer* m_baseText;
			TextBuffer* m_editText;
		};
	}
}

#endif