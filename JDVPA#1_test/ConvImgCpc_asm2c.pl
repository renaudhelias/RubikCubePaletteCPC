# perl ConvImgCpc_asm2c.pl pacman_sprites.asm

my $fichier_asm = $ARGV[0];
$fichier_asm =~ m/^(.+)\.asm$/;
$fichier_c = "$1.c";
$fichier_h = "$1.h";

print "Cibles : $fichier_c et $fichier_h\n\n";

open(my $fh, "<", $fichier_asm) or die "plouf $!";
while (my $ligne = <$fh>) {
	chomp $ligne;
	print "$ligne\n";
}
open(my $cfh,">","outch.".$fichier_c) or die "pouitch $fichier_c $!";
open(my $hfh,">","outch.".$fichier_h) or die "pouitch $fichier_h $!";
print $cfh "du C !\n";
print $hfh "du H !\n";
close($hfh);
close($ch);
close($fh);