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