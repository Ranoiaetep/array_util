//
// Created by Peter Cong on 1/13/22.
//

#pragma once
#include <array>
#include <utility>
#include <functional>

template<std::size_t Size, typename T>
constexpr auto arr_fill(T value);

template<std::size_t Size, typename T>
constexpr auto arr_seq(T init);

template<std::size_t N, typename Func, typename T>
constexpr auto multi_invoke(Func&& func, T init);

template<std::size_t Size, typename T, typename Func>
constexpr auto arr_gen(T init, Func&& func);

template<std::size_t N, typename T>
constexpr bool arr_equal(std::array<T, N> const& arr1, std::array<T, N> const& arr2);

namespace Detail
{
    template<typename T, std::size_t ... I>
    constexpr auto arr_fill_impl(T value, std::index_sequence<I...>)
    {
        return std::array<T, sizeof...(I)>{(I, value)...};
    }

    template<typename T, T ... I>
    constexpr auto arr_seq_impl(T init, std::integer_sequence<T, I...>)
    {
        return std::array{(I + init)...};
    }

    template<typename Func>
    struct Func_Wrapper
    {
        Func func;

        template<typename T>
        [[nodiscard]] constexpr auto operator|(T init) const noexcept
        {
            return func(init);
        }
    };

    template<typename T, typename Func, std::size_t ... I>
    constexpr auto multi_invoke_helper(T init, Func func, std::index_sequence<I...>)
    {
        constexpr auto f = Func_Wrapper<Func>{func};
        return ((I, f) | ... | init);
    }

    template<typename T, typename Func, std::size_t ... I>
    constexpr auto arr_gen_impl(T init, Func&& func, std::index_sequence<I...>)
    {
        return std::array{multi_invoke<I>(std::forward<Func>(func), init)...};
    }

    template<std::size_t N, typename T, std::size_t ... I>
    constexpr bool arr_equal_impl(std::array<T, N> const& arr1, std::array<T, N> const& arr2, std::index_sequence<I...>)
    {
        return ((arr1[I] == arr2[I]) && ...);
    }
}

template<std::size_t Size, typename T>
constexpr auto arr_fill(T value)
{
    return Detail::arr_fill_impl(value, std::make_index_sequence<Size>{});
}

template<std::size_t Size, typename T>
constexpr auto arr_seq(T init)
{
    return Detail::arr_seq_impl(init, std::make_integer_sequence<T, Size>{});
}

template<std::size_t N, typename Func, typename T>
constexpr auto multi_invoke(Func&& func, T init)
{
    return Detail::multi_invoke_helper(init, std::forward<Func>(func), std::make_index_sequence<N>{});
}

template<std::size_t Size, typename T, typename Func>
constexpr auto arr_gen(T init, Func&& func)
{
    return Detail::arr_gen_impl(init, std::forward<Func>(func), std::make_index_sequence<Size>{});
}

template<std::size_t N, typename T>
constexpr bool arr_equal(std::array<T, N> const& arr1, std::array<T, N> const& arr2)
{
    return Detail::arr_equal_impl(arr1, arr2, std::make_index_sequence<N>{});
}