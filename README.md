# Utf-8-converter
Program that encodes unicode integers in utf-8.
There is a choice between:
1)encoding an integer (symbol's unicode number) in utf-8 OR
2)converting a pre-selected 386intel.txt file to utf-8.
The 386intel.txt is encoded using asc-II table 473 (for symbols 128-255).
This program looks at the position(ints) of the symbols in 473 and switches them
To their unicode positions (unicode ints).
Then it encodes those numbers in utf-8 and writes that code as a char 1 byte at a time (2 hex digis = 8 bites)
into a new file, completing the conversion.
