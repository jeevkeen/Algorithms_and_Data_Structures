#pragma once

#ifndef STACK_ON_MASS_HPP
#define STACK_ON_MASS_HPP

#include <cstddef>
#include <stdexcept>

namespace StackOnMass {

    template <typename T>
    class TStackOnMass {
    private:
        T* _data; //указатель на димнамический массив в пам€ти, где физически хран€тс€ элементы
        size_t _capacity;
        size_t _top;      //указывает на индекс следующей свободной €чейки и текущее количество элементов в стеке

    public:
        explicit TStackOnMass(size_t capacity = 10); //explicit вызовет ошибку, если попытаемс€ написать размер через равно
        TStackOnMass(const TStackOnMass& other);
        TStackOnMass& operator=(const TStackOnMass& other);
        ~TStackOnMass();

        void push(const T& val);
        T pop();
        T& top();
        const T& top() const; //read-only доступ дл€ случаем, когда происходит вызов неизмен€емого стека (чтобы не было ошибки)

        inline bool is_empty() const noexcept;
        inline bool is_full() const noexcept;
    };

    template <typename T>
    TStackOnMass<T>::TStackOnMass(size_t capacity)
        : _capacity(capacity), _top(0) { //_capacity = capacity;
        if (capacity == 0) {
            throw std::invalid_argument("Stack capacity must be > 0");
        }
        _data = new T[_capacity];
    }

    template <typename T>
    TStackOnMass<T>::TStackOnMass(const TStackOnMass<T>& other)
        : _capacity(other._capacity), _top(other._top) {
        _data = new T[_capacity];
        for (size_t i = 0; i < _top; ++i) {
            _data[i] = other._data[i];
        }
    }

    template <typename T>
    TStackOnMass<T>& TStackOnMass<T>::operator=(const TStackOnMass<T>& other) {
        if (this != &other) {
            T* new_data = new T[other._capacity];
            for (size_t i = 0; i < other._top; ++i) {
                new_data[i] = other._data[i];
            }
            delete[] _data;

            _data = new_data;
            _capacity = other._capacity;
            _top = other._top;
        }
        return *this;
    }

    template <typename T>
    TStackOnMass<T>::~TStackOnMass() {
        delete[] _data;
    }

    template <typename T>
    void TStackOnMass<T>::push(const T& val) {
        if (is_full()) {
            throw std::overflow_error("Error push: stack overflow");
        }
        _data[_top++] = val;
    }

    template <typename T>
    T TStackOnMass<T>::pop() {
        if (is_empty()) {
            throw std::underflow_error("Error pop: stack is empty");
        }
        return _data[--_top];
    }

    template <typename T>
    T& TStackOnMass<T>::top() {
        if (is_empty()) {
            throw std::underflow_error("Error top: stack is empty");
        }
        return _data[_top - 1];
    }

    template <typename T>
    const T& TStackOnMass<T>::top() const {
        if (is_empty()) {
            throw std::underflow_error("Error top: stack is empty");
        }
        return _data[_top - 1];
    }

    template <typename T>
    inline bool TStackOnMass<T>::is_empty() const noexcept {
        return _top == 0;
    }

    template <typename T>
    inline bool TStackOnMass<T>::is_full() const noexcept {
        return _top == _capacity;
    }

}

#endif