# -*- encoding: utf-8 -*-

#
# extconf.rb
#
# Copyright 2012 Krzysztof Wilczynski
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

require 'mkmf'

RbConfig::MAKEFILE_CONFIG['CC'] = ENV['CC'] if ENV['CC']

$CFLAGS << ' -g -Wall'

have_header('ruby.h') or missing('ruby.h')

dir_config('fizzbuzz')

create_header
create_makefile('fizzbuzz/fizzbuzz')

# vim: set ts=2 sw=2 sts=2 et :
# encoding: utf-8
