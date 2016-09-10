#!/usr/bin/perl

use strict;
use warnings;

package CScan;

use vars qw($VERSION @ISA @EXPORT);
require Exporter;
@ISA = qw(Exporter);
@EXPORT = qw(test);

sub test {
	print "Whoa!! \n";
}


1;
