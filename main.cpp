#include "my_virtual_classes.h"

VIRTUAL_CLASS(Base)
  int a = 42;
  CONSTRUCT(Base)
    ADD_FUNC(Base, Both)
    ADD_FUNC(Base, OnlyBase)
  END

  DECLARE_METHOD(Base, Both)
    std::cout << curr->a <<"\n";
  END


  DECLARE_METHOD(Base, OnlyBase)
  END

END

VIRTUAL_CLASS_DERIVED(Derived, Base)
  int b = 1;

  DERIVED_CONSTRUCT(Derived, Base)
    DERIVED_ADD_FUNC(Derived, Both)
    DERIVED_ADD_FUNC(Derived, OnlyDerived)
  END

  DECLARE_METHOD(Derived, Both)
    std::cout << curr->b <<"\n";
  END

  DECLARE_METHOD(Derived, OnlyDerived)
  END
END

int main() {
  Base base;
  Derived derived;

  // полиморфизм
  Base* reallyDerived = reinterpret_cast<Base*>(&derived);
  
  VIRTUAL_CALL(&base, Both); // печатает “Base::Both a = 0”
  VIRTUAL_CALL(reallyDerived, Both); // печатает “Derived::Both b = 1”
  VIRTUAL_CALL(reallyDerived, OnlyBase);  // печатает “Base::OnlyBase”
  VIRTUAL_CALL(reallyDerived, OnlyDerived); // бросает исключение

  return 0;
}
