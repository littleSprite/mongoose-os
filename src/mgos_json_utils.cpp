/*
 * Copyright (c) 2020 Deomid "rojer" Ryabkov
 * All rights reserved
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "common/json_utils.h"

namespace mgos {

int JSONPrinterString(struct json_out *out, const char *buf, size_t len) {
  std::string *res = static_cast<std::string *>(out->u.data);
  res->append(buf, len);
  return len;
}

std::string JSONPrintfString(const char *fmt, ...) {
  std::string res;
  struct json_out out = {};
  va_list ap;
  va_start(ap, fmt);
  out.printer = JSONPrinterString;
  out.u.data = reinterpret_cast<char *>(&res);
  json_vprintf(&out, fmt, ap);
  va_end(ap);
  res.shrink_to_fit();
  return res;
}

}  // namespace mgos
