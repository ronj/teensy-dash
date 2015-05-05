#pragma once

namespace Common
{
	template <typename T>
	class List
	{
	public:
		List()
			: m_Head(nullptr)
			, m_Tail(nullptr)
			, m_Iterator(nullptr)
		{
		}

		~List()
		{
			for (T* it = GetFirst(); it != nullptr; it = GetNext())
			{
				Remove(it);
			}
		}

		class Element
		{
			friend class List<T>;

		public:
			virtual ~Element();

		protected:
			Element(T& data)
				: m_Data(data)
				, m_Next(nullptr)
				, m_Prev(nullptr)
				, m_ParentList(nullptr)
			{
			}

		private:
			T& m_Data;
			volatile Element* m_Next;
			volatile Element* m_Prev;
			volatile List* m_ParentList;
		};

		class Iterator
		{
		public:
			Iterator(T* element, List* parent)
				: m_Element(element)
				, m_ParentList(parent)
			{
			}

			Iterator(const Iterator& it)
				: m_Element(it.m_Element)
				, m_ParentList(it.m_ParentList)
			{
			}

			Iterator& operator++()
			{
				m_Element = m_ParentList->GetNext();
				return *this;
			}

			Iterator operator++(int)
			{
				Iterator tmp(*this);
				operator++();
				return tmp;
			}

			bool operator==(const Iterator& rhs)
			{
				return m_Element == rhs.m_Element;
			}

			bool operator!=(const Iterator& rhs)
			{
				return m_Element != rhs.m_Element;
			}

			T& operator*()
			{
				return *m_Element;
			}

		private:
			T* m_Element;
			List* m_ParentList;
		};

		Iterator begin()
		{
			return Iterator(GetFirst(), this);
		}

		Iterator end()
		{
			return Iterator(nullptr, this);
		}

		bool IsEmpty() const
		{
			return m_Head == nullptr;
		}

		T* GetFirst()
		{
			if (m_Head)
			{
				m_Iterator = m_Head;
				return GetNext();
			}

			return nullptr;
		}

		T* GetNext()
		{
			if (m_Iterator)
			{
				T* ret = &m_Iterator->m_Data;
				m_Iterator = m_Iterator->m_Next;
				return ret;
			}

			return nullptr;
		}

		T* GetLast()
		{
			if (m_Tail)
			{
				m_Iterator = m_Tail;
				return GetPrevious();
			}

			return nullptr;
		}

		T* GetPrevious()
		{
			if (m_Iterator)
			{
				T* ret = &m_Iterator->m_Data;
				m_Iterator = m_Iterator->m_Prev;
				return ret;
			}

			return nullptr;
		}

		void Add(Element& element)
		{
			Add(&element);
		}

		void Add(Element* element)
		{
			if (element->m_ParentList)
			{
				return;
			}

			element->m_ParentList = this;
			element->m_Next = nullptr;
			element->m_Prev = m_Tail;

			if (m_Tail)
			{
				m_Tail->m_Next = element;
			}
			else
			{
				m_Head = element;
			}

			m_Tail = element;
		}

		void Remove(Element& element)
		{
			Remove(&element);
		}

		void Remove(Element* element)
		{
			if (element->m_ParentList != this)
			{
				return;
			}

			if (m_Iterator == element)
			{
				m_Iterator = element->m_Next;
			}

			if (element->m_Prev)
			{
				element->m_Prev->m_Next = element->m_Next;
			}
			else
			{
				m_Head = element->m_Next;
				if (m_Head)
				{
					m_Head->m_Prev = nullptr;
				}
			}

			if (element->m_Next)
			{
				element->m_Next->m_Prev = element->m_Prev;
			}
			else
			{
				m_Tail = element->m_Prev;
				if (m_Tail)
				{
					m_Tail->m_Next = nullptr;
				}
			}

			element->m_ParentList = nullptr;
			element->m_Prev = nullptr;
			element->m_Next = nullptr;
		}

	private:
		volatile Element* m_Head;
		volatile Element* m_Tail;
		volatile Element* m_Iterator;
	};

	template <typename T>
	List<T>::Element::~Element()
	{
		if (m_ParentList)
		{
			((List<T>*)m_ParentList)->Remove((List<T>::Element*)this);
		}
	}
}
