# perl ConvImgCpc_asm2c.pl pacman_sprites.asm

my $fichier_asm = $ARGV[0];
$fichier_asm =~ m/^(.+)\.asm$/;
$fichier_c = "$1.c";
$fichier_h = "$1.h";
my $majuscules=uc($1);
print "Cibles : $fichier_c et $fichier_h\n\n";

open(my $fh, "<", $fichier_asm) or die "plouf $!";
open(my $cfh,">","outch.".$fichier_c) or die "pouitch $fichier_c $!";
open(my $hfh,">","outch.".$fichier_h) or die "pouitch $fichier_h $!";

print $hfh "#ifndef ${majuscules}_H\n";
print $hfh "#define ${majuscules}_H\n\n";
print $hfh "extern const unsigned char ${1}[];\n\n";
print $hfh "#endif\n";
close($hfh);

while (my $ligne = <$fh>) {
	chomp $ligne;
	print "$ligne\n";
}

print $cfh "du C !\n";

close($ch);
close($fh);