#include "api.h"
#include "textdocument.h"

bool CreateTextDocument(ITextDocument **ppDoc)
{
	if (!ppDoc)
		return false;

	*ppDoc = new lightpad::TextDocument;
	return true;
}

void DestroyTextDocument(ITextDocument *pDoc)
{
	if (pDoc)
		delete pDoc;
}

