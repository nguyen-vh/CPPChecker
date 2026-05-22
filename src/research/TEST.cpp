
#include <iostream>

#include "../../include/cxxchecker_reflection.hpp"

namespace check {

class XClass {
 public:
 protected:
  int foo;

 private:
};

std::string zloo;

namespace check2 {

struct XXClass {
 private:
  double gloo(int);
};

}  // namespace check2

}  // namespace check

class YClass {
 private:
  double foo;
};

long int zoo(signed int);

auto main(int /*argc*/, char* /*argv*/[]) -> int {
  std::cout << class_has_membervar<"XClass"_ls, "foo"_ls>;
  std::cout << " FALSE" << std::endl;
  std::cout << class_has_membervar<"XClass"_ls, "foo"_ls, int>;
  std::cout << " FALSE" << std::endl;

  std::cout << class_has_membervar<"check::XClass"_ls, "foo"_ls>;
  std::cout << " TRUE" << std::endl;
  std::cout << class_has_membervar<"check::XClass"_ls, "foo"_ls, int>;
  std::cout << " TRUE" << std::endl;

  std::cout << class_has_membervar<"YClass"_ls, "foo"_ls>;
  std::cout << " TRUE" << std::endl;

  std::cout << std::endl;

  std::cout << class_has_memberfunc<"check::check2::XXClass"_ls, "gloo"_ls>;
  std::cout << " TRUE" << std::endl;

  std::cout
      << class_has_memberfunc<"check::check2::XXClass"_ls, "gloo"_ls, double>;
  std::cout << " TRUE" << std::endl;

  std::cout << class_has_memberfunc<"check::check2::XXClass"_ls, "gloo"_ls,
                                    double, int>;
  std::cout << " TRUE" << std::endl;

  std::cout
      << class_has_memberfunc<"check::check2::XXClass"_ls, "gloo"_ls, int>;
  std::cout << " FALSE" << std::endl;

  std::cout << class_has_memberfunc<"check::check2::XXClass"_ls, "gloo"_ls,
                                    double, float>;
  std::cout << " FALSE" << std::endl;

  std::cout << std::endl;

  std::cout << has_free_function<"zoo"_ls>;
  std::cout << " TRUE" << std::endl;

  std::cout << has_free_function<"zoo"_ls, long int>;
  std::cout << " TRUE" << std::endl;

  std::cout << has_free_function<"zoo"_ls, long int, int>;
  std::cout << " TRUE" << std::endl;

  std::cout << std::endl;

  std::cout << has_free_variable<"check::zloo"_ls>;
  std::cout << " TRUE - No namespace breakdown yet" << std::endl;

  return 0;
}
