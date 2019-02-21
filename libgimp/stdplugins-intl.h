/*
 * Names of this file and directory mean nothing,
 * because this is a dummy path to maintain difference.
 */

/* trap for source compatibility */
//#ifndef GETTEXT_PACKAGE
//#error "config.h must be included prior to stdplugins-intl.h"
//#endif

//#include "gettext.h"

#define _(String) (String)
#define N_(String) (String)
#define INIT_I18N() {}
#define GETTEXT_PACKAGE NULL
