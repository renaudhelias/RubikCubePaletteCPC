# perl ConvImgCpc_asm2c.pl Pacman_reduce.asm

my $fichier_asm = $ARGV[0];
$fichier_asm =~ m/^(.+)\.asm$/;
my $majuscules=uc($1."_sprites");
my $minuscules=lc($1."_sprites");
$fichier_c = "$minuscules.c";
$fichier_h = "$minuscules.h";
print "Cibles : $fichier_c et $fichier_h\n";

open(my $fh, "<", $fichier_asm) or die "plouf $!";
open(my $cfh,">",$fichier_c) or die "pouitch $fichier_c $!";
open(my $hfh,">",$fichier_h) or die "pouitch $fichier_h $!";

print $hfh "#ifndef ${majuscules}_H\n";
print $hfh "#define ${majuscules}_H\n\n";
print $hfh "extern const unsigned char ${minuscules}[];\n\n";
print $hfh "#endif\n";
close($hfh);

print $cfh "const unsigned char ${minuscules}[]=\n";
print $cfh "{\n";

my $first_time=1;

while (my $ligne = <$fh>) {
	chomp $ligne;
	# google "perl regex match string"
	if ($ligne =~ m/^;/) {
		print $cfh "    // ".$ligne."\n";
	# google "perl regex capture string"
	} elsif ($ligne =~ m/^[ ]*DB/) {
		$ligne =~ m/^[ ]*DB[ ]*#(..), #(..), #(..), #(..), #(..), #(..), #(..), #(..)$/;
		if ($first_time) {
			$first_time=0;
			print $cfh "      0x$1, 0x$2, 0x$3, 0x$4, 0x$5, 0x$6, 0x$7, 0x$8\n";
		} else {
			print $cfh "    , 0x$1, 0x$2, 0x$3, 0x$4, 0x$5, 0x$6, 0x$7, 0x$8\n";
		}
	}
	# print "$ligne\n";
}

print $cfh "};\n";

close($ch);
close($fh);