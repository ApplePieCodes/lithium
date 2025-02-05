#pragma once

void init_term();
void twrite(const char *c);
void twrite_ok(const char *c);
void twrite_info(const char *c);
void twrite_warn(const char *c);
void twrite_error(const char *c);
void tclear();