#include <iostream>
#include <memory>
#include <typeinfo>

class Any {
public:
    Any() : content(nullptr) {}
    template<typename T>
	// make_unique, чтобы за памятью не следить XD
    Any(const T& value) : content(std::make_unique<Holder<T>>(value)) {}
	
	// скрываем этот тип T
    template<typename T>
    T get() const {
        if (typeid(T) != content->type()) {
            throw std::bad_cast();
        }
        return static_cast<Holder<T>*>(content.get())->value;
    }

private:
    struct BaseHolder {
        virtual ~BaseHolder() = default;
        virtual const std::type_info& type() const = 0;
    };
    template<typename T>
    struct Holder : BaseHolder {
        Holder(const T& value) : value(value) {}
        const std::type_info& type() const override {
            return typeid(T);
        }
        
        T value;
    };

    std::unique_ptr<BaseHolder> content;
};


int main(){
	// Те тип мы изначально не  знаем
	// Работает только при указании верного типа
	Any a(5);
	std::cout << a.get<int>() << std::endl; // 5
	try{
		a.get<std::string>();
	}
	catch (std::bad_cast){
		std::cout << "Cought bad cast\n";
	}
}
