#ifndef LIGHTPAD_API_H
#define LIGHTPAD_API_H

#include <core/itextdocument.h>

LP_API bool CreateTextDocument(ITextDocument **ppDoc);
LP_API void DestroyTextDocument(ITextDocument *pDoc);

#endif // LIGHTPAD_API_H
