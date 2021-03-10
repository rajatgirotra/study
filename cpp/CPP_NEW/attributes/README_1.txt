C++11/14 have tried to standardize attributes.
attributes are just a special syntax supported by your compiler that helps the compiler generate code/warnings etc that the
developer intends and also gives the code reviewer an understanding of what the developer is intending.

You would seen in GCC.

struct S {
...
} __attribute__((packed)); // this is GCC way

__attribute__((pure));
__attribute__((noreturn));
__attribute__((aligned(8))); etc etc..


Similarly MSVS has its own way, example
 __declspec(deprecated)

 So C++11 standardized all this. attributes can be applied to almost everything.
 1) function declarations
 2) types
 3) enums
 4) variables etc.

 Let's see the most common ones

 [[noreturn]] void terminate() noexcept;  --> tells the compiler that the function does not return
========================================================================================================================
 [[maybe_unused]] --> can be applied to variables/functions/function parameters and tells the compiler not to generate a warning if the
 variables/functions/function parameter is un-used.

 [[maybe_unused]] static void foo();

 int main() {
 [[maybe_unused]] int a = 42;
 }

 int main([[maybe_unused]] int argc, char** argv) {
 }
 ========================================================================================================================
 [[deprecated]] or [[deprecated("some msg")]] --> will tell the compiler to emit a warning if a deprecated class or function or namespace is used

 namespace [[deprcated("use Awesomenamepace instead"]] GoodNamspace {}
 ========================================================================================================================

 [[fallthrough]] --> used in switch case to tell a fallthrough is intentional
 switch (ch) {
     case 'a':
     [[fallthrough]]
     case 'b': break;
 }
 ========================================================================================================================
 [[nodiscard]] --> tells the compiler to emit a warning if the result of a function is discarded. This is mostly used when the function
 might allocate a resource and discarding the result would result in resource leak.
 example:

 [[nodiscard]] void* malloc(size_t bytes);
 [[nodiscard]] std::future<T> std::async();

 enum class [[nodiscard]] ErrorCode { // can also be applied to a type. Now any function which returns this type is implicitly [[nodiscard]]
     OK,
     Fatal,
     System,
     FileIssue
 };
     ErrorCode OpenFile(std::string_view fileName);
     ErrorCode SendEmail(std::string_view sendto,
     std::string_view text);
     ErrorCode SystemCall(std::string_view text);
 ========================================================================================================================