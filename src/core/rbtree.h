
#ifndef LIGHTPAD_RBTREE_H
#define LIGHTPAD_RBTREE_H

namespace lightpad
{
	namespace core
	{
		enum rbtree_node_color
		{
			red,
			black
		};

		struct rbtree_node_base
		{
			rbtree_node_color color;
			rbtree_node_base* parent;
			rbtree_node_base* left;
			rbtree_node_base* right;
		};

		template<typename T = rbtree_node_base>
		class node_op
		{
		public:
			static inline rbtree_node_ptr left(rbtree_node_ptr node)
			{
				return (rbtree_node_ptr)node->left;
			}

			static inline void set_left(rbtree_node_ptr parent, rbtree_node_ptr child)
			{
				parent->left = child;
			}

			static inline rbtree_node_ptr right(rbtree_node_ptr node)
			{
				return (rbtree_node_ptr)node->right;
			}

			static inline void set_right(rbtree_node_ptr parent, rbtree_node_ptr child)
			{
				parent->right = child;
			}

			static inline rbtree_node_ptr parent(rbtree_node_ptr node)
			{
				return (rbtree_node_ptr)node->parent;
			}

			static inline rbtree_node_ptr set_parent(rbtree_node_ptr child, rbtree_node_ptr parent)
			{
				child->parent = parent;
			}

			static rbtree_node_ptr left_most(rbtree_node_ptr node)
			{
				while (node && left(node)) node = left(node);
				return node;
			}

			static rbtree_node_ptr right_most(rbtree_node_ptr node)
			{
				while (node && right(node)) node = right(node);
				return node;
			}
		};

		template<typename T = rbtree_node_base>
		class rbtree_iterator : public std::iterator<std::bidirectional_iterator_tag, T>
		{
			typedef T* rbtree_node_ptr;
			typedef T& rbtree_node_ref;
			typedef node_op<T> op;
		public:
			rbtree_iterator(rbtree_node_ptr node)
				: m_node(node)
			{

			}

			rbtree_iterator(const rbtree_iterator& it)
				: m_node(it.m_node)
			{

			}

			rbtree_iterator& operator++()
			{
				_increment();
				return *this;
			}

			rbtree_iterator operator++(int)
			{
				rbtree_iterator it(*this);
				_increment();
				return it;
			}

			rbtree_iterator& operator--()
			{
				_decrement();
				return *this;
			}

			rbtree_iterator operator--(int)
			{
				rbtree_iterator it(*this);
				_decrement();
				return it;
			}

			inline bool operator==(const rbtree_iterator& it)
			{
				return this->m_node == it.m_node;
			}

			inline bool operator!=(const rbtree_iterator& it)
			{
				return this->m_node != it.m_node;
			}

			inline rbtree_node_ref operator*() const
			{
				return *m_node;
			}

			inline rbtree_node_ptr operator->() const
			{
				return m_node;
			}

		private:
			void _increment()
			{
				if (right(m_node))
				{
					m_node = op::right(m_node);
					m_node = op::left_most(m_node);
				}
				else
				{
					rbtree_node_ptr parent = op::parent(m_node);
					while (m_node == op::right(parent))
					{
						m_node = parent;
						parent = op::parent(parent);
					}
					if (op::right(m_node) == parent)
						m_node = parent;
				}
			}

			void _decrement()
			{
				if (m_node->color == red && op::parent(op::parent(m_node)) == m_node)
				{
					m_node = op::right(m_node);
				}
				else if (op::left(m_node) != nullptr) 
				{
					rbtree_node_ptr y = op::left(m_node);
					m_node = op::right_most(y);
				}
				else 
				{
					rbtree_node_ptr y = op::parent(m_node);
					while (m_node == op:left(y))
					{
						m_node = y;
						y = op::parent(y);
					}
					m_node = y;
				}
			}

		private:
			rbtree_node_ptr m_node = nullptr;
		};

		template<typename T = rbtree_node_base>
		class rbtree_op_base : public node_op<T>
		{
			typedef T* rbtree_node_ptr;
		public:
			static void left_rotate(rbtree_node_ptr x, rbtree_node_ptr& root)
			{
				rbtree_node_ptr y = right(x);
				set_right(x, left(y));
				if (left(y))
					set_parent(left(y), x);
				set_parent(y, parent(x));

				if (x == root)
					root = y;
				else if (x == left(parent(x)))
					set_left(parent(x), y);
				else
					set_right(parent(x), y);

				set_left(y, x);
				set_parent(x, y);
			}

			static void right_rotate(rbtree_node_ptr x, rbtree_node_ptr& root)
			{
				rbtree_node_ptr y = left(x);
				set_left(x, right(y));
				if (right(y))
					set_parent(right(y), x);
				set_parent(y, parent(x));

				if (x == root)
					root = y;
				else if (x == right(parent(x)))
					set_right(parent(x), y);
				else
					set_left(parent(x), y);

				set_right(y, x);
				set_parent(x, y);
			}

			static void rebalance_for_insert(rbtree_node_ptr x, rbtree_node_ptr& root)
			{
				x->color = red;
				while (x != root && parent(x)->color == red)
				{
					if (parent(x) == left(parent(parent(x))))
					{
						rbtree_node_ptr y = right(parent(parent(x)));
						if (y && y->color == red)
						{
							parent(x)->color = black;
							y->color = black;
							parent(parent(x))->color = red;
							x = parent(parent(x));
						}
						else
						{
							if (x == right(parent(x)))
							{
								x = parent(x);
								left_rotate(x, root);
							}

							parent(x)->color = black;
							parent(parent(x))->color = red;
							right_rotate(parent(parent(x)), root);
						}
					}
					else
					{
						rbtree_node_ptr y = left(parent(parent(x)));
						if (y && y->color == red)
						{
							parent(x)->color = black;
							y->color = black;
							parent(parent(x))->color = red;
							x = parent(parent(x));
						}
						else
						{
							if (x == left(parent(x)))
							{
								x = parent(x);
								right_rotate(x, root);
							}

							parent(x)->color = black;
							parent(parent(x))->color = red;
							left_rotate(parent(parent(x)), root);
						}
					}
				}
				root->color = black;
			}

			static rbtree_node_ptr rebalance_for_erase(
				rbtree_node_ptr z,
				rbtree_node_ptr& root,
				rbtree_node_ptr& leftmost,
				rbtree_node_ptr& rightmost)
			{
				rbtree_node_ptr y = z;
				rbtree_node_ptr x = nullptr;
				rbtree_node_ptr x_parent = nullptr;
				if (left(y) == nullptr)
				{
					x = right(y);
				}
				else if (right(y) == nullptr)
				{
					x = left(y);
				}
				else
				{
					y = right(y);
					while (left(y))
						y = left(y);
					x = right(y);
				}

				if (y != z)
				{
					set_parent(left(z), y);
					set_left(y, left(z));
					if (y != right(z))
					{
						x_parent = parent(y);
						if (x)
							set_parent(x, parent(y));
						set_left(parent(y), x);
						set_right(y, right(z));
						set_parent(right(z), y);
					}
					else
					{
						x_parent = y;
					}

					if (root == z)
						root = y;
					else if (left(parent(z)) == z)
						set_left(parent(z), y);
					else
						set_right(parent(z), y);
					set_parent(y, parent(z));
					std::swap(y->color, z->color);
					y = z;
				}
				else
				{
					x_parent = parent(y);
					if (x) set_parent(parent(y));
					if (root == z)
						root = x;
					else if (left(parent(z)) == z)
						set_left(parent(z), x);
					else
						set_right(parent(z), x);
					if (leftmost == z)
					{
						if (right(z) == nullptr)
							leftmost = parent(z);
						else
							leftmost = left_most(x);
					}
					if (rightmost == z)
					{
						if (left(z) == nullptr)
							rightmost = parent(z);
						else
							rightmost = right_most(x);
					}
				}

				if (y->color != red)
				{
					while (x != root && (x == nullptr || x->color == black))
					{
						if (x == left(x_parent))
						{
							rbtree_node_ptr w = right(x_parent);
							if (w->color == red)
							{
								w->color = black;
								x_parent->color = red;
								left_rotate(x_parent, root);
								w = right(x_parent);
							}
							if ((left(w) == nullptr || left(w)->color == black) &&
								(right(w) == nullptr || right(w)->color == black))
							{
								w->color = red;
								x = x_parent;
								x_parent = parent(x_parent);
							}
							else
							{
								if (right(w) == nullptr || right(w)->color == black)
								{
									if (left(w))
										left(w)->color = black;
									w->color = red;
									right_rotate(w, root);
									w = right(x_parent);
								}
								w->color = x_parent->color;
								x_parent->color = black;
								if (right(w)) right(w)->color = black;
								left_rotate(x_parent, root);
								break;
							}
						}
						else {
							rbtree_node_ptr w = left(x_parent);
							if (w->color == red)
							{
								w->color = black;
								x_parent->color = red;
								right_rotate(x_parent, root);
								w = left(x_parent);
							}
							if ((right(w) == nullptr || right(w)->_M_color == black) &&
								(left(w) == nullptr || left(w)->color == black))
							{
								w->color = red;
								x = x_parent;
								x_parent = parent(x_parent);
							}
							else
							{
								if (left(w) == nullptr || left(w)->color == black)
								{
									if (right(w))
										right(w)->color = black;
									w->color = red;
									left_rotate(w, root);
									w = left(x_parent);
								}
								w->color = x_parent->color;
								x_parent->color = black;
								if (left(w))
									left(w)->color = black;
								right_rotate(x_parent, root);
								break;
							}
						}
					}

					if (x)
						x->color = black;
				}
				return y;
			}
		};

		template<typename T = rbtree_node_base, template<typename> typename tree_op = rbtree_op_base>
		class rbtree
		{
			typedef T rbtree_node;
			typedef T* rbtree_node_ptr;
			typedef tree_op<T> rbtree_op;
		};
	}
}

#endif // LIGHTPAD_RBTREE_H
