#!/usr/bin/perl
use strict;
use warnings;

package Filetree;

sub addFile {
	my $fTree = shift;
	my $fName = shift;

	return if defined $fTree->{$fName};

	$fTree->{$fName} = {};
}

sub addIncludedFile {
	my $fTree = shift;
	my $fName = shift;
	my $incFName = shift;

	# Prevent accidental auto-adding of, say, a header file.
	return unless defined $fTree->{$fName};

	$fTree->{$fName}->{includes}->{$incFName} = 1;
}
sub addReferencingFile {
	my $fTree = shift;
	my $fName = shift;
	my $incFName = shift;

	# Prevent accidental auto-adding of, say, a header file.
	return unless defined $fTree->{$fName};

	$fTree->{$fName}->{included_by}->{$incFName} = 1;
}

sub getFiles {
	my $fTree = shift;

	return keys($fTree);
}

return 1;
