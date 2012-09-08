#ifndef MARSHAL_H
#define MARSHAL_H

#include <glib-object.h>

G_BEGIN_DECLS
/* VOID:DOUBLE */
extern 
void mdispgtk_marshal_VOID__DOUBLE (GClosure     *closure,
                                    GValue       *return_value,
                                    guint         n_param_values,
                                    const GValue *param_values,
                                    gpointer      invocation_hint,
                                    gpointer      marshal_data);

/* VOID:INT,INT,INT,INT,INT,INT */
extern
void mdispgtk_marshal_VOID__INT_INT_INT_INT (GClosure     *closure,
                                             GValue       *return_value,
                                             guint         n_param_values,
                                             const GValue *param_values,
                                             gpointer      invocation_hint,
                                             gpointer      marshal_data);

/* VOID:INT,INT,INT,INT,DOUBLE,DOUBLE */
extern
void mdispgtk_marshal_VOID__INT_INT_DOUBLE_DOUBLE (GClosure     *closure,
                                                   GValue       *return_value,
                                                   guint         n_param_values,
                                                   const GValue *param_values,
                                                   gpointer      invocation_hint,
                                                   gpointer      marshal_data);

G_END_DECLS

#endif
