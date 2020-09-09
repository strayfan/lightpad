
#ifndef LIGHTPAD_TEXT_BUFFER_H
#define LIGHTPAD_TEXT_BUFFER_H

#include <vector>
#include <algorithm>

namespace lightpad
{
	namespace core
	{
		enum { PAGE_SIZE = 4096 };

		template<typename T>
		class TextPage
		{
			typedef T value_type;
			enum { PAGE_CAPACITY = PAGE_SIZE / sizeof(value_type) };
		public:
			value_type buffer[PAGE_CAPACITY];
		};

		template<typename T>
		class TextBuffer
		{
			typedef T value_type;
			typedef TextPage<value_type> Page;
			enum { PAGE_CAPACITY = PAGE_SIZE / sizeof(value_type) };

		public:
			TextBuffer()
				: m_pLast(nullptr)
				, m_pEnd(nullptr)
			{

			}

			~TextBuffer()
			{
				for (Page* page : m_pages)
					delete page;
				m_pages.clear();
			}

		public:
			void append(value_type val)
			{
				if (m_pLast == m_pEnd)
					_createTextPage();

				*m_pLast++ = val;
			}
			template<typename _Iter>
			void append(_Iter it, _Iter itEnd)
			{
				size_t remain = std::distance(it, itEnd);
				while (remain != 0)
				{
					if (m_pLast == m_pEnd)
						_createTextPage();

					_Iter itCur = it;
					size_t len = std::min(remain, m_pEnd - m_pLast);

					std::advance(it, len);
					std::copy(itCur, it, m_pLast);
					m_pLast += len;
					remain -= len;
				}
			}

		private:
			void _createTextPage()
			{
				Page* page = new Page;
				m_pages.emplace_back(page);
				m_pLast = page->buffer;
				m_pEnd = m_pLast + PAGE_CAPACITY;
			}

		private:
			std::vector<Page*> m_pages;
			value_type* m_pLast;
			value_type* m_pEnd;
		};
	}
}

#endif