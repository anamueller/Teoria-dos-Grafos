# Python program to find
# maximal Bipartite matching.

from posixpath import split


class GFG:
	def __init__(self,graph):
		
		# residual graph
		self.graph = graph
		self.crianca = len(graph)
		self.brinquedos = len(graph[0])

	# A DFS based recursive function
	# that returns true if a matching
	# for vertex u is possible
	def bpm(self, u, matchR, seen):

		# Try every job one by one
		for v in range(self.brinquedos):

			# If applicant u is interested
			# in job v and v is not seen
			if self.graph[u][v] and seen[v] == False:
				
				# Mark v as visited
				seen[v] = True

				'''If job 'v' is not assigned to
				an applicant OR previously assigned
				applicant for job v (which is matchR[v])
				has an alternate job available.
				Since v is marked as visited in the
				above line, matchR[v] in the following
				recursive call will not get job 'v' again'''
				if matchR[v] == -1 or self.bpm(matchR[v],
											matchR, seen):
					matchR[v] = u
					return True
		return False

	# Returns maximum number of matching
	def maxBPM(self):
		'''An array to keep track of the
		applicants assigned to jobs.
		The value[0] of matchR[i] is the
		applicant number assigned to job i,
		the value[0] -1 indicates nobody is assigned.'''
		matchR = [-1] * self.brinquedos
		
		# Count of jobs assigned to applicants
		result = 0
		for i in range(self.crianca):
			
			# Mark all jobs as not seen for next applicant.
			seen = [False] * self.brinquedos
			
			# Find if the applicant 'u' can get a job
			if self.bpm(i, matchR, seen):
				result += 1
		return result

N, M, L=[int(k) for k in input().split()]
crianca_e_brinquedos = [[0 for _ in range(M)] for _ in range(N)]
for i in range(L):
    c, b = [int(k) for k in input().split()]
    crianca_e_brinquedos[c][b]=1

g = GFG(crianca_e_brinquedos)

print (g.maxBPM())

# This code is contributed by Neelam Yadav
