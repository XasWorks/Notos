#!/usr/bin/perl
use strict;
use warnings;

use FNameOps;
use Filetree;

package Scanning;

my $scanEnv = {};

sub setWorkEnvironment {
	my $newWenv = shift;
	die "Not a HASH ref!" unless ref $newWenv == 'HASH';

	$workEnv->{scanning} = {} unless defined $workEnv->{scanning};
	$scanEnv = $workEnv->{scanning};

	$scanEnv->{unscanned} = [] unless defined $scanEnv->{unscanned};
	$scanEnv->{scanned} = {} unless defined $scanEnv->{scanned};
}

sub hasBeenScanned {
	my $fName = shift;
	die "No filename given!" unless defined $fName;
	die "Working environment not set!" unless defined $workEnv;

	return $scanEnv->{scanned}->{$fName} == 1;
}
sub markAsScanned {
	my $fName = shift;
	die "No filename given!" unless defined $fName;
	die "Working environment not set!" unless defined $workEnv;

	$scanEnv->{scanned}->{$fName} = 1;
}

sub queue {
	my $fName = shift;
	die "No filename given!" unless defined $fName;
	die "Working environment not set!" unless defined $workEnv;

	push $scanEnv->{queued}, $fName;
}
sub hasQueued {
	die "Working environment not set!" unless defined $workEnv;

	return @{$scanEnv->{queued}} > 0;
}
sub popQueue {
	die "Working environment not set!" unless defined $workEnv;

	return pop $scanEnv->{queued} if hasQueued;
	return undef;
}



return 1;
