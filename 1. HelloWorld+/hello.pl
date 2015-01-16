# 1. Done
#Note : Very little error feedback given when I forgot the semicolon!

$greeting = "Hello" . ","; # Concatenation can also be used between string and numbers
$greeting = "$greeting world!"; # Note : 'single quotes' would not have evaluated the string scalar
print "$greeting\n";
