# TASK

1. Make an RPNsolver that takes a string of numbers and operators(+,-,/,*) and outputs the result.
2. Extend the supported operators with 'sum', 'log', '^', 'swap', 'sin', 'cos', 'dup'
3. Extend the supported numbers to include 'pi' and 'e'

Notes:

		22-((5+2)*3) = 1					==>>        '22 5 2 + 3 * -'
		1/(Sin(Pi/4))^2 = 2					==>>        'Pi 4 / sin 2 ^ 1 swap /'
		1/((Sin(Pi/6)/Cos(Pi/6))^2) = 3		==>> 		'Pi 6 / dup sin swap cos / 2 ^ 1 swap /'


