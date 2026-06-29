// RUN: %clang_cc1 -fsyntax-only -verify -std=c++20 %s

// This test ensures that DesignatedInitUpdateExpr properly propagates dependence
// and doesn't crash when used inside a template.

template <int N>
void f() {
    struct Point { int x, y; };
    struct Rect { Point p1, p2; };
    
    // Using a C99/GNU extension where an initializer overrides a previous one.
    // This creates a DesignatedInitUpdateExpr in the AST.
    constexpr Rect r = { .p1 = {1, 2}, .p1.x = N }; // expected-warning {{nested designators are a C99 extension}} \
                                                    // expected-warning {{initializer overrides prior initialization of this subobject}} \
                                                    // expected-note {{previous initialization is here}}
    static_assert(r.p1.x == N, "");
}

void g() {
    f<3>(); // expected-note {{in instantiation of function template specialization 'f<3>' requested here}}
}
