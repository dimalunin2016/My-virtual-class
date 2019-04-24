#include <iostream>
#include <cassert>
#include <functional>
#include <unordered_map>

#define VIRTUAL_CLASS(name)                                         \
  struct name {                                                     \
    const static int type_ = 0;                                     \
    std::unordered_map<std::string,                                 \
     std::pair<std::function<void(void *)>, int > > virtual_table_; \


#define END };

#define CONSTRUCT(name)                                             \
  name() {                                                          \

#define ADD_FUNC(class_name, func_name)                             \
    virtual_table_[#func_name] =                                    \
    std::make_pair(std::function<void(void *)>(this->func_name), 0);


#define DECLARE_METHOD(class_name, func_name)                       \
  static void func_name(void *class_ptr) {                          \
    class_name* curr = reinterpret_cast<class_name *>(class_ptr);   \
    std::cout << #class_name <<"::" << #func_name <<"\n";           \


#define VIRTUAL_CLASS_DERIVED(derive_name, basic_name)              \
  struct derive_name {                                              \
    const static int type_ = 1;                                     \
    std::unordered_map<std::string,                                 \
          std::pair<std::function<void(derive_name *)>,             \
                                            int> > virtual_table_;


#define DERIVED_CONSTRUCT(derive_name, basic_name)                  \
    derive_name() {                                                 \
      basic_name basic_class;                                       \
      for (auto it = basic_class.virtual_table_.begin(); it !=      \
           basic_class.virtual_table_.end(); ++it) {                \
        virtual_table_[it->first] =                                 \
          std::make_pair(                                           \
          std::function<void(derive_name *)>(it->second.first), 0); \
      }

#define DERIVED_ADD_FUNC(derive_name, func_name)                    \
    if (virtual_table_.find(#func_name) != virtual_table_.end()) {  \
      virtual_table_[#func_name] =                                  \
      std::make_pair(                                               \
          std::function<void(derive_name *)>(this->func_name), -1); \
    } else {                                                        \
      virtual_table_[#func_name] =                                  \
       std::make_pair(                                              \
           std::function<void(derive_name *)>(this->func_name), 1); \
    }


#define VIRTUAL_CALL(class_ptr, func_name)                          \
  if ((class_ptr)->type_ >=                                         \
      (class_ptr)->virtual_table_[#func_name].second) {             \
    ((class_ptr)->virtual_table_[#func_name].first)(class_ptr);     \
  } else {                                                          \
    std::cout << "No such function" <<"\n";                         \
    assert(0);                                                      \
  }

