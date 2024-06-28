#![no_std] // We're on our on from here on out!
#![no_main]

use core::panic::PanicInfo;

mod vga_buffer;

// No name mangleing
#[no_mangle]
pub extern "C" fn _start() -> ! {
    println!("Hello World{}", "!");
    loop {}
}

#[panic_handler]
fn panic(info: &PanicInfo) -> ! {
    println!("{}", info);
    loop {}
}