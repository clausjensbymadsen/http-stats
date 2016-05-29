HTTP Statistics
================
HTTP Statistics analyzes Apache-like web server access logs.
It is designed to be fast and to be able to handle huge log files.

Usage
-----
For basic usage, simply type
```
http-stats access.log
```
to analyze the access log file named "access.log".

For advanced usage, run `http-stats -help`.

Development
-----------
The application is developed in C++14 (and using the `std::string_view` from C++17) and built with CMake.

The application is using the Google Test framework for unit testing.

License
-------
This project is covered by the [MIT license](LICENSE).