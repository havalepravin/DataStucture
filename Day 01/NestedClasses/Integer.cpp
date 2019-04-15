#include <iostream>
class Integer {
public:
	class IntegerPrinter {
	public:
		IntegerPrinter(Integer &integer) : m_integer(integer) {}
	public:
		void print() {
			std::cout << m_integer.m_i << std::endl;
		}
	private:
		Integer &m_integer;
	};
public:
	Integer(int i = 0) : m_i(i) {}
private:
	int m_i;
};

int main() {
	Integer a(10);
	Integer::IntegerPrinter intPrinter(a);
	intPrinter.print();
}
