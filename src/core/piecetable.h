
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
			typedef TextBuffer<UTF16> U16TextBuffer;
		public:
			PieceTable();
			~PieceTable();

		private:
			U16TextBuffer* m_baseText;
			U16TextBuffer* m_editText;
		};
	}
}

#endif
