// RUN: %clang_cc1 -fsyntax-only -verify %s

template<typename T>
struct test {
    typedef void(* type)(T); // expected-error {{pointer to function type 'void () const' cannot have 'const' qualifier}}
};

typedef void foo_t() const;

typedef test<foo_t>::type func_t; // expected-note {{in instantiation of template class 'test<void () const>' requested here}}

template<typename F>
struct create_pointer {
    typedef void func_t(F); // expected-error {{pointer to function type 'void () const' cannot have 'const' qualifier}}
    template<typename X>
    struct extract {
        typedef X type;
    };
    typedef typename extract<func_t>::type type;
};

int main() {
    create_pointer<void() const>::type p = 0; // expected-note {{in instantiation of template class 'create_pointer<void () const>' requested here}}
}
