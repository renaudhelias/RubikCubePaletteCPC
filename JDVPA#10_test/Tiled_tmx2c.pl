# perl Tiled_tmx2c.pl labyPac.tmx

my $fichier_tmx = $ARGV[0];
$fichier_tmx =~ m/^(.+)\.tmx$/;
my $majuscules=uc($1."_map");
my $minuscules=lc($1."_map");
$fichier_c = "$minuscules.c";
$fichier_h = "$minuscules.h";
print "Cibles : $fichier_c et $fichier_h\n";

open(my $fh, "<", $fichier_tmx) or die "plouf $!";
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
	if ($ligne =~ m/^[ ]*</) {
		print $cfh "    // ".$ligne."\n";
	# google "perl regex capture string"
	} elsif ($ligne =~ m/^[0-9]/) {
		$ligne =~ m/^([0-9]+),([0-9]+),([0-9]+),([0-9]+),([0-9]+),([0-9]+),([0-9]+),([0-9]+),([0-9]+),([0-9]+),([0-9]+),([0-9]+),([0-9]+),([0-9]+),([0-9]+),([0-9]+),([0-9]+),([0-9]+),([0-9]+),([0-9]+),([0-9]+),([0-9]+),([0-9]+),([0-9]+),([0-9]+),([0-9]+),([0-9]+),([0-9]+),([0-9]+),([0-9]+),([0-9]+),([0-9]+),([0-9]+),([0-9]+),([0-9]+),([0-9]+),([0-9]+),([0-9]+),([0-9]+),([0-9]+),*$/;
		if ($first_time) {
			$first_time=0;
			print $cfh "      $1, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12, $13, $14, $15, $16, $17, $18, $19, $20, $21, $22, $23, $24, $25, $26, $27, $28, $29, $30, $31, $32, $33, $34, $35, $36, $37, $38, $39, $40\n";
		} else {
			print $cfh "    , $1, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12, $13, $14, $15, $16, $17, $18, $19, $20, $21, $22, $23, $24, $25, $26, $27, $28, $29, $30, $31, $32, $33, $34, $35, $36, $37, $38, $39, $40\n";
		}
	}
	# print "$ligne\n";
}

print $cfh "};\n";

close($ch);
close($fh);