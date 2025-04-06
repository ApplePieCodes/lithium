#![no_std]
#![no_main]

pub mod arch;

pub fn kmain() {
    loop {
        
    }
}

#[panic_handler]
fn rust_panic(_info: &core::panic::PanicInfo) -> ! {
    loop {
        
    }
}