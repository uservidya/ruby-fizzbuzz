/*
 fizzbuzz.c

 Copyright 2012 Krzysztof Wilczynski

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*/

#include <fizzbuzz.h>

ID id_at_start, id_at_stop;
VALUE rb_cFizzBuzz = Qnil;

void Init_fizzbuzz(void);

static void validate_limit(VALUE value);
static VALUE evaluate_value(int value);
static VALUE return_values(VALUE object, return_t type);

VALUE
fizzbuzz_initialize(int argc, VALUE *argv, VALUE object)
{
  VALUE start, stop;

  rb_scan_args(argc, argv, "11", &start, &stop);

  if (NIL_P(start) || NIL_P(stop))
    rb_raise(rb_eArgError, errors[E_MISSING_ARGUMENTS]);

  CHECK_TYPE(start, errors[E_INVALID_START_TYPE])
  CHECK_TYPE(stop, errors[E_INVALID_STOP_TYPE])

  CHECK_BOUNDARY(start, stop, errors[E_INCORRECT_START_STOP])

  rb_ivar_set(object, id_at_start, start);
  rb_ivar_set(object, id_at_stop, stop);

  return object;
}

VALUE
fizzbuzz_get_start(VALUE object)
{
  return rb_ivar_get(object, id_at_start);
}

VALUE
fizzbuzz_set_start(VALUE object, VALUE value)
{
  int stop = rb_ivar_get(object, id_at_stop);

  CHECK_TYPE(value, errors[E_INVALID_START_TYPE])
  CHECK_BOUNDARY(value, stop, errors[E_INCORRECT_START])

  rb_ivar_set(object, id_at_start, value);
  return Qnil;
}

VALUE
fizzbuzz_get_stop(VALUE object)
{
  return rb_ivar_get(object, id_at_stop);
}

VALUE
fizzbuzz_set_stop(VALUE object, VALUE value)
{
  int start = rb_ivar_get(object, id_at_start);

  CHECK_TYPE(value, errors[E_INVALID_STOP_TYPE])
  CHECK_BOUNDARY(start, value, errors[E_INCORRECT_STOP])

  rb_ivar_set(object, id_at_stop, value);
  return Qnil;
}

VALUE
fizzbuzz_to_array(VALUE object)
{
  return return_values(object, R_TYPE_ARRAY);
}

VALUE
fizzbuzz_to_enumerator(VALUE object)
{
  return return_values(object, R_TYPE_ENUMERATOR);
}

VALUE
fizzbuzz_is_fizz(VALUE object, VALUE value)
{
  CHECK_TYPE(value, errors[E_INVALID_TYPE])
  return IS_FIZZ(FIX2INT(value)) ? Qtrue : Qfalse;
}

VALUE
fizzbuzz_is_buzz(VALUE object, VALUE value)
{
  CHECK_TYPE(value, errors[E_INVALID_TYPE])
  return IS_BUZZ(FIX2INT(value)) ? Qtrue : Qfalse;
}

VALUE
fizzbuzz_is_fizzbuzz(VALUE object, VALUE value)
{
  CHECK_TYPE(value, errors[E_INVALID_TYPE])
  return IS_FIZZBUZZ(FIX2INT(value)) ? Qtrue : Qfalse;
}

VALUE
fizzbuzz_square(VALUE object, VALUE value)
{
  CHECK_TYPE(value, errors[E_INVALID_TYPE])
  return evaluate_value(FIX2INT(value));
}

static VALUE
evaluate_value(int value)
{
  VALUE result = Qnil;

  if (value == 0)
    return INT2FIX(value);

  int score = SCORE_VALUE(value);

  switch(score) {
    case 0:
      result = INT2FIX(value);
      break;
    case 1:
      result = rb_str_new2(words[score - 1]);
      break;
    case 2:
      result = rb_str_new2(words[score - 1]);
      break;
    case 3:
      result = rb_str_new2(words[score - 1]);
      break;
  }

  return result;
}

static VALUE
return_values(VALUE object, return_t type)
{
  int i;
  int start = FIX2INT(rb_ivar_get(object, id_at_start));
  int stop  = FIX2INT(rb_ivar_get(object, id_at_stop));

  VALUE array;
  VALUE value = Qnil;

  if (WANT_ARRAY(type)) {
    array = rb_ary_new();
  }
  else {
    RETURN_ENUMERATOR(object, 0, 0);
  }

  for (i = start; i <= stop; i++) {
    value = evaluate_value(i);
    WANT_ARRAY(type) ? rb_ary_push(array, value) : rb_yield(value);
  }

  return WANT_ARRAY(type) ? array : object;
}

void
Init_fizzbuzz(void)
{
  id_at_start = rb_intern("@start");
  id_at_stop  = rb_intern("@stop");

  rb_cFizzBuzz = rb_define_class("FizzBuzz", rb_cObject);

  rb_include_module(rb_cFizzBuzz, rb_mEnumerable);

  rb_define_const(rb_cFizzBuzz, "VERSION", rb_str_new2(FIZZBUZZ_VERSION));

  rb_define_method(rb_cFizzBuzz, "initialize", fizzbuzz_initialize, -1);

  rb_define_method(rb_cFizzBuzz, "start", fizzbuzz_get_start, 0);
  rb_define_method(rb_cFizzBuzz, "start=", fizzbuzz_set_start, 1);
  rb_define_method(rb_cFizzBuzz, "stop", fizzbuzz_get_stop, 0);
  rb_define_method(rb_cFizzBuzz, "stop=", fizzbuzz_set_stop, 1);

  rb_define_method(rb_cFizzBuzz, "to_a", fizzbuzz_to_array, 0);
  rb_define_method(rb_cFizzBuzz, "each", fizzbuzz_to_enumerator, 0);

  rb_define_singleton_method(rb_cFizzBuzz, "is_fizz?", fizzbuzz_is_fizz, 1);
  rb_define_singleton_method(rb_cFizzBuzz, "is_buzz?", fizzbuzz_is_buzz, 1);
  rb_define_singleton_method(rb_cFizzBuzz, "is_fizzbuzz?", fizzbuzz_is_fizzbuzz, 1);

  rb_define_singleton_method(rb_cFizzBuzz, "[]", fizzbuzz_square, 1);
}
