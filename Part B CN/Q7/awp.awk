BEGIN {
}
{
if($6 == "cwnd_")
{
print $1 , $7 >> "file.tr"
printf("%f\t%f\n", $1, $7);

}
}
END {
}
