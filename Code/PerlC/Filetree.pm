#!/usr/bin/perl
use strict;
use warnings;

package Filetree;

my $fTreeEnv = {};

sub setWorkEnvironment {
	my $newWenv = shift;
	die "Not a HASH ref!" unless ref $newWenv == 'HASH';

	$workEnv->{files} = {} unless defined $workEnv->{files};
	$fTreeEnv = $workEnv->{files};
}

sub addFile {
	my $fName = shift;
	die "No filename given!" unless defined $fName;
	die "Working environment not set!" unless defined $fTreeEnv;

	return if defined $fTree->{$fName};

	$fTree->{$fName} = {};
}

sub addIncludedFile {
	my $fName = shift;
	my $incFName = shift;
	die "No filename given!" unless defined $fName and defined $incFName;
	die "Working environment not set!" unless defined $fTreeEnv;

	# Prevent accidental auto-adding of, say, a header file.
	return unless defined $fTree->{$fName};

	$fTree->{$fName}->{includes}->{$incFName} = 1;
}
sub addReferencingFile {
	my $fName = shift;
	my $incFName = shift;
	die "No filename given!" unless defined $fName and defined $incFName;
	die "Working environment not set!" unless defined $fTreeEnv;

	# Prevent accidental auto-adding of, say, a header file.
	return unless defined $fTree->{$fName};

	$fTree->{$fName}->{included_by}->{$incFName} = 1;
}

sub getFiles {
	die "Working environment not set!" unless defined $fTreeEnv;

	return keys($fTree);
}

return 1;
