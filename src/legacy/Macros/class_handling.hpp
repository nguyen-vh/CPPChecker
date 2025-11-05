#ifndef CLASS_HANDLING_HPP
#define CLASS_HANDLING_HPP

//* Checks for the Existence of a Class
#define M_CLASS_HANDLING                                                       \
  template <typename T>                                                        \
  bool check_class() {                                                         \
    std::string strClassN = typeid(T).name(), strClassNreadable{};             \
    strClassN = strClassN.erase(0, 9);                                         \
    for (int i = 0; i < strClassN.length(); ++i) {                             \
      if (std::isdigit(strClassN[i])) {                                        \
        if (!std::isdigit(strClassN[i + 1])) {                                 \
          strClassNreadable = strClassN.substr(i + 1);                         \
        }                                                                      \
      }                                                                        \
    }                                                                          \
    strClassNreadable.pop_back();                                              \
    if (!std::is_same<T, TASK::TESTER::No>::value) {                           \
      std::cout << "+ Class '" << strClassNreadable << "' found" << std::endl; \
      return true;                                                             \
    } else {                                                                   \
      std::cout << "- Class in Assignment not found. " << std::endl;           \
      return false;                                                            \
    }                                                                          \
  }

#endif