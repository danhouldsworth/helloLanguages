# TASK

1. Make an RPNsolver that takes a string of numbers and operators(+,-,/,*) and outputs the result.
2. Extend the supported operators with 'sum', 'log', '^', '<>', 'sin', 'cos', 'dup', '!'
3. Extend the supported numbers to include 'pi' and 'e'

Notes:

        1 === 5 / ( 4 + ( 3 - ( 2 * 1 ) ) )                             ==>>  '5 4 3 2 1 / + - *'
        2 === ( ( Sin( Pi / 4 ) ) ^ 2 ) * 4                             ==>>  'pi 4 / sin 2 ^ 4 *'
        3 === 1 / ( ( Sin( Pi / Fact(3) ) / Cos( Pi / Fact(3) ) ) ^ 2 ) ==>>  '1 pi 3 ! / dup sin <> cos / 2 ^ /'

