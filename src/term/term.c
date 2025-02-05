#include <stdarg.h>
#include <kmain.h>
#include <term/backends/fb.h>
#include <term/flanterm.h>
#include <utils/spinlock.h>
#include <utils/panic.h>
#include <libc/string.h>
#include <term/term.h>

struct flanterm_context *ft_ctx;
lock_t term_lock;

void twrite(const char *c) {
    spinlock_lock(&term_lock);
    ft_ctx->set_text_fg_rgb(ft_ctx, 0xD3D7CF);
    flanterm_write(ft_ctx, c, strlen(c));
    spinlock_unlock(&term_lock);
}

void twrite_info(const char *c) {
    spinlock_lock(&term_lock);
    ft_ctx->set_text_fg_rgb(ft_ctx, 0xD3D7CF);
    flanterm_write(ft_ctx, "[INFO] ", 8);
    flanterm_write(ft_ctx, c, strlen(c));
    flanterm_write(ft_ctx, "\n", 2);
    spinlock_unlock(&term_lock);
}

void twrite_warn(const char *c) {
    spinlock_lock(&term_lock);
    ft_ctx->set_text_fg_rgb(ft_ctx, 0xC4A000);
    flanterm_write(ft_ctx, "[WARNING] ", 11);
    flanterm_write(ft_ctx, c, strlen(c));
    flanterm_write(ft_ctx, "\n", 2);
    spinlock_unlock(&term_lock);
}

void twrite_error(const char *c) {
    spinlock_lock(&term_lock);
    ft_ctx->set_text_fg_rgb(ft_ctx, 0xCC0000);
    flanterm_write(ft_ctx, "[ERROR] ", 9);
    flanterm_write(ft_ctx, c, strlen(c));
    flanterm_write(ft_ctx, "\n", 2);
    spinlock_unlock(&term_lock);
}

void twrite_ok(const char *c) {
    spinlock_lock(&term_lock);
    ft_ctx->set_text_fg_rgb(ft_ctx, 0x4E9A06);
    flanterm_write(ft_ctx, "[OK] ", 6);
    flanterm_write(ft_ctx, c, strlen(c));
    flanterm_write(ft_ctx, "\n", 2);
    spinlock_unlock(&term_lock);
}

void tclear() {
    spinlock_lock(&term_lock);
    ft_ctx->clear(ft_ctx, true);
    spinlock_unlock(&term_lock);
}

void init_term() {
    spinlock_lock(&term_lock);
    if (framebuffer_request.response->framebuffer_count < 1) {
        panic("No Framebuffer Provided", "FRAME_BFR_NULL", PANIC_HALT);
    }

    struct limine_framebuffer *framebuffer = framebuffer_request.response->framebuffers[0];

    ft_ctx = flanterm_fb_init(NULL, NULL, framebuffer->address, framebuffer->width, framebuffer->height, framebuffer->pitch, framebuffer->red_mask_size, framebuffer->red_mask_shift, framebuffer->green_mask_size, framebuffer->green_mask_shift, framebuffer->blue_mask_size, framebuffer->blue_mask_shift, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 0, 0, 0);

    spinlock_unlock(&term_lock);
}