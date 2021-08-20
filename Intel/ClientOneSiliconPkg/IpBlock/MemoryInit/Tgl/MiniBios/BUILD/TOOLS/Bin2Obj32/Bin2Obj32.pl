# ==============================================================
# utility to generate obj 32 out of BIOS ROM file
#
# usage:
#   perl Bin2Obj32.pl <input binary file> <output obj file>

# example:
#   perl Bin2Obj32.pl M0028_03.ROM M0028_03.obj
# ==============================================================
# p1 - input binary ROM file
# p2 - output obj 32 obj format
# ==============================================================

use strict;
my $binFile = shift || die "p1 - no input bin file\n";
my $outFile = shift || die "p2 - no output obj file\n";

my $buffer;
my @bufferArray;

# Dec2Hex
#####################################################################################
sub dec2hex { return sprintf("%02x", @_[0] ); }

print "opening $binFile\n";
open(FILE, "$binFile") || die $!;
open (OUTFILE, ">$outFile" ) || die $!;

binmode( FILE );
read(FILE, $buffer, 1024 * 1024);
close(FILE);

foreach (split(//, $buffer)) {
  push @bufferArray,dec2hex(ord($_));
}

printObj32( 0x00000000 );
printObj32( 0xFFF00000 );
print OUTFILE "/eof\n";

close (OUTFILE);

#####################################################################################
sub printObj32() {
   my $lineSplit = 0;

   # base is 4G - 1M
   my $base = shift;
   printf(OUTFILE "/origin %08X\n",$base/4);
   my $countHoleStart = 0;
   my $countHoleInLine = 0;
   my $counter = 0;
   my @tempList = ();
   my $saveLine = "";

   foreach (@bufferArray) {
     $counter++;
     if (($counter % 0x1000) == 0) {
       printf "\rGenerating output: %06x",$counter;
     }
     push @tempList, $_;
     if (@tempList == 4) {
       # little endian reverse of dword
       my $item =  join "", reverse @tempList;
       @tempList = ();
       # save all dwords in $saveLine for later use
       $saveLine = $saveLine . " " . $item;

       # count the number of ffffffff in line into $countHoleInLine
       if ($item eq "ffffffff") { $countHoleInLine++ }

       $lineSplit++;
       if ($lineSplit == 4) {

          # check that we have this line:
          # ffffffff ffffffff ffffffff ffffffff
          if ($countHoleInLine == 4) {
             # print nothing (counting the hole size)
             $countHoleStart = 1;
          } else {
             if ($countHoleStart == 1) {
                $countHoleStart = 0;
                printf(OUTFILE "/origin %06x\n", $base/4);
             }
             print OUTFILE $saveLine, "\n";
          }

         $saveLine = "";
         $countHoleInLine=0;
         $lineSplit = 0;
         $base+=0x10;
       }
     }
   }
   print "\n";
}


