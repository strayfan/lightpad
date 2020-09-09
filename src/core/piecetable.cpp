
#include "piecetable.h"

namespace lightpad
{
	namespace core
	{
		PieceTable::PieceTable()
			: m_baseText(nullptr)
			, m_editText(nullptr)
		{

		}

		PieceTable::~PieceTable()
		{
			delete m_baseText;
			delete m_editText;
		}
	}
}