#include <type_traits>
#include <cstdint>

// Основной шаблон are_same, который по умолчанию наследует std::false_type
template <typename...>
struct are_same : std::false_type {};

// Частичная специализация для случая одного типа
template <typename T>
struct are_same<T> : std::true_type {};

// Частичная специализация для случая нескольких типов
template <typename T, typename U, typename... Rest>
struct are_same<T, U, Rest...> 
    : std::conditional_t<
          std::is_same_v<std::remove_cvref_t<T>, std::remove_cvref_t<U>>,
          are_same<U, Rest...>,
          std::false_type
      > 
{};

// Упрощение для доступа к значению через constexpr переменную
template <typename... Ts>
constexpr bool are_same_v = are_same<Ts...>::value;

static_assert(are_same_v<int, int32_t, signed int>, "compile assert");
static_assert(!are_same_v<char, const int, int&>, "compile assert");  // тут не равны из !  

