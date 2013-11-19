# -*- encoding: utf-8 -*-

# :stopdoc:

#
# range.rb
#
# Copyright 2012-2013 Krzysztof Wilczynski
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

# :startdoc:

#
# Provides a convenient integration of _FizzBuzz_ with _Range_ class.
#
class Range
  #
  # call-seq:
  #    range.fizzbuzz( reverse )                  -> array
  #    range.fizzbuzz( reverse ) {|value| block } -> self
  #
  # Returns either an array or accepts a block if such is given. When a block is given
  # then it will call the block once for each subsequent value for a given range, passing
  # the value as a parameter to the block.
  #
  # Additionally, if the value of +reverse+ is set to be +true+ then the results will
  # be given in an <em>reverse order</em> whether in a resulting array or when passing
  # values to a block given.
  #
  # Example:
  #
  #    (1..15).fizzbuzz         #=> [1, 2, "Fizz", 4, "Buzz", "Fizz", 7, 8, "Fizz", "Buzz", 11, "Fizz", 13, 14, "FizzBuzz"]
  #    (1..15).fizzbuzz(true)   #=> ["FizzBuzz", 14, 13, "Fizz", 11, "Buzz", "Fizz", 8, 7, "Fizz", "Buzz", 4, "Fizz", 2, 1]
  #
  # Example:
  #
  #    (1..15).fizzbuzz {|value| puts "Got #{value}" }
  #
  # Produces:
  #
  #    Got 1
  #    Got 2
  #    Got Fizz
  #    Got 4
  #    Got Buzz
  #    Got Fizz
  #    Got 7
  #    Got 8
  #    Got Fizz
  #    Got Buzz
  #    Got 11
  #    Got Fizz
  #    Got 13
  #    Got 14
  #    Got FizzBuzz
  #
  # See also: FizzBuzz::fizzbuzz, FizzBuzz#to_a, FizzBuzz#each and FizzBuzz#reverse_each
  #
  def fizzbuzz(reverse = false)
    values = self.collect {|i| FizzBuzz[i] }.send(reverse ? :reverse : :entries)

    if block_given?
      values.each {|i| yield i }
      self
    else
      values
    end
  end
end

# :enddoc:

# vim: set ts=2 sw=2 sts=2 et :
# encoding: utf-8
