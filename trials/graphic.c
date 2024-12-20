#include "../myproject/CwebStudio"

struct CwebHttpResponse *main_sever(struct CwebHttpRequest *request ){

    struct CTextStack *s = newCTextStack(CTEXT_LINE_BREAKER, CTEXT_SEPARATOR);


    s->$open(s,HTML,"lang=\"en\"");
        s->open(s,H1);
            s->segment_text(s,"Hello Seth");
        s->close(s,H1);
    s->close(s,HTML);
    return cweb_send_rendered_CTextStack_cleaning_memory(s,200);
}

CWEB_START_MACRO(5000, main_sever)