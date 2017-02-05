#!/usr/bin/perl

use strict;
use warnings;

package FNameOps;

sub cleanPath {
	my $fName = shift;
	
	my $hasImpurity;
	while(1) {
		$hasImpurity = 0;

		if($fName =~ /[\w\-]+\/\.\.\//) {
			$fName =~ s/[\w\-]+\/\.\.\///;
			$hasImpurity = 1;
		}
		if($fName =~ /\/\//) {
			$fName =~ s/\/\//\//;
			$hasImpurity = 1;
		}

		return $fName unless $hasImpurity;
	}
}
sub getPath {
  my $fName = cleanPath shift;
  $fName =~ s/[\w\-\.]+$/\//;
  return $fName;
}

sub stripEnd {
	my $fName = cleanPath shift;

	$fName =~ s/\.\w+$//;
	return $fName;
}

sub getName() {
	my $fName = cleanPath shift;

	$fName =~ s/^\/?([\w-]+\/)//;
	return $fName;
}

sub getMatching {
	my $fName = cleanPath shift;

	$fName = stripEnd($fName);

	foreach(@_) {
		my $fNameEnded = $fName . "." . $_;
		return $fNameEnded if( -f $fNameEnded );
	}

	return 0;
}


return 1;
