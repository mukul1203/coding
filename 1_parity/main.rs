// This is a comment. Line comments look like this...
// and extend multiple lines like this.

/* Block comments
  /* can be nested. */ */

/// Documentation comments look like this and support markdown notation.
/// # Examples
///
/// ```
/// let five = 5
/// ```

///////////////
// 1. Basics //
///////////////

#[allow(dead_code)]
// Functions
// `i32` is the type for 32-bit signed integers
// fn add2(x: i32, y: i32) -> i32 {
//     // Implicit return (no semicolon)
//     x + y
// }

#[allow(unused_variables)]
#[allow(unused_assignments)]
#[allow(dead_code)]
// Main function
fn main() {
    // Numbers //

    // Immutable bindings
    // let x: i32 = 1;

    // Integer/float suffixes
    // let y: i32 = 13i32;
    // let f: f64 = 1.3f64;

    // Type inference
    // let implicit_x = 1;
    // let implicit_f = 1.3;

    // Arithmetic
    // let sum = x + y + 13;

    // Mutable variable
    // let mut mutable = 1;
    // mutable = 4;
    // mutable += 2;

    // Strings //

    // String literals
    // let x: &str = "hello world!";

    // Printing
    // println!("{} {}", f, x); // 1.3 hello world

    // A `String` – a heap-allocated string
    // let s: String = "hello world".to_string();

    // A string slice – an immutable view into another string
    // let s_slice: &str = &s;

    // println!("{} {}", s, s_slice); // hello world hello world

    // Vectors/arrays //

    // A fixed-size array
    // let four_ints: [i32; 4] = [1, 2, 3, 4];

    // A dynamic array (vector)
    // let mut vector: Vec<i32> = vec![1, 2, 3, 4];
    // vector.push(5);

    // A slice – an immutable view into a vector or array
    // let slice: &[i32] = &vector;

    // Use `{:?}` to print something debug-style
    // println!("{:?} {:?}", vector, slice); // [1, 2, 3, 4, 5] [1, 2, 3, 4, 5]

    // Tuples //

    // A tuple is a fixed-size set of values of possibly different types
    // let x: (i32, &str, f64) = (1, "hello", 3.4);

    // Destructuring `let`
    // let (a, b, c) = x;
    // println!("{} {} {}", a, b, c); // 1 hello 3.4

    // Indexing
    // println!("{}", x.1); // hello

    //////////////
    // 2. Types //
    //////////////

    // Struct
    // struct Point {
    //     x: i32,
    //     y: i32,
    // }

    // let origin: Point = Point { x: 0, y: 0 };

    // A struct with unnamed fields, called a ‘tuple struct’
    // struct Point2(i32, i32);

    // let origin2 = Point2(0, 0);

    // Basic C-like enum
    // enum Direction {
    //     Left,
    //     Right,
    //     Up,
    //     Down,
    // }

    // let up = Direction::Up;

    // Enum with fields
    // enum OptionalI32 {
    //     AnI32(i32),
    //     Nothing,
    // }

    // let two: OptionalI32 = OptionalI32::AnI32(2);
    // let nothing = OptionalI32::Nothing;

    // Generics //

    // struct Foo<T> { bar: T }

    // enum Optional<T> {
    //     SomeVal(T),
    //     NoVal,
    // }

    // Methods //

    // impl<T> Foo<T> {
    //     fn bar(&self) -> &T { // self is borrowed
    //         &self.bar
    //     }
    //     fn bar_mut(&mut self) -> &mut T { // self is mutably borrowed
    //         &mut self.bar
    //     }
    //     fn into_bar(self) -> T { // here self is consumed
    //         self.bar
    //     }
    // }

    // let a_foo = Foo { bar: 1 };
    // println!("{}", a_foo.bar()); // 1

    // Traits //

    // trait Frobnicate<T> {
    //     fn frobnicate(self) -> Option<T>;
    // }

    // impl<T> Frobnicate<T> for Foo<T> {
    //     fn frobnicate(self) -> Option<T> {
    //         Some(self.bar)
    //     }
    // }

    // let another_foo = Foo { bar: 1 };
    // println!("{:?}", another_foo.frobnicate()); // Some(1)

    // Function pointer types // 

    // fn fibonacci(n: u32) -> u32 {
    //     match n {
    //         0 => 1,
    //         1 => 1,
    //         _ => fibonacci(n - 1) + fibonacci(n - 2),
    //     }
    // }

    // type FunctionPointer = fn(u32) -> u32;

    // let fib : FunctionPointer = fibonacci;
    // println!("Fib: {}", fib(4)); // 5

    /////////////////////////
    // 3. Pattern matching //
    /////////////////////////

    // let foo = OptionalI32::AnI32(1);
    // match foo {
    //     OptionalI32::AnI32(n) => println!("it’s an i32: {}", n),
    //     OptionalI32::Nothing  => println!("it’s nothing!"),
    // }

    // Advanced pattern matching
    // struct FooBar { x: i32, y: OptionalI32 }
    // let bar = FooBar { x: 15, y: OptionalI32::AnI32(32) };

    // match bar {
    //     FooBar { x: 0, y: OptionalI32::AnI32(0) } =>
    //         println!("The numbers are zero!"),
    //     FooBar { x: n, y: OptionalI32::AnI32(m) } if n == m =>
    //         println!("The numbers are the same"),
    //     FooBar { x: n, y: OptionalI32::AnI32(m) } =>
    //         println!("Different numbers: {} {}", n, m),
    //     FooBar { x: _, y: OptionalI32::Nothing } =>
    //         println!("The second number is Nothing!"),
    // }

    /////////////////////
    // 4. Control flow //
    /////////////////////

    // `for` loops/iteration
    // let array = [1, 2, 3];
    // for i in array {
    //     println!("{}", i);
    // }

    // Ranges
    // for i in 0u32..10 {
    //     print!("{} ", i);
    // }
    // println!("");
    // prints `0 1 2 3 4 5 6 7 8 9 `

    // `if`
    // if 1 == 1 {
    //     println!("Maths is working!");
    // } else {
    //     println!("Oh no...");
    // }

    // `if` as expression
    // let value = if true {
    //     "good"
    // } else {
    //     "bad"
    // };

    // `while` loop
    // while 1 == 1 {
    //     println!("The universe is operating normally.");
    //     break
    // }

    // Infinite loop
    // loop {
    //     println!("Hello!");
    //     break
    // }

    /////////////////////////////////
    // 5. Memory safety & pointers //
    /////////////////////////////////

    // Owned pointer
    // let mut mine: Box<i32> = Box::new(3);
    // *mine = 5;
    // let mut now_its_mine = mine;
    // *now_its_mine += 2;

    // println!("{}", now_its_mine); // 7

    // Reference
    // let mut var = 4;
    // var = 3;
    // let ref_var: &i32 = &var;

    // println!("{}", var);
    // println!("{}", *ref_var);
    // ref_var;
    // var = 2;

    // Mutable reference
    // let mut var2 = 4;
    // let ref_var2: &mut i32 = &mut var2;
    // *ref_var2 += 2;

    // println!("{}", *ref_var2); // 6
    // ref_var2;
}