define a1
	display exec->stdout_fd
	display exec->stdin_fd
	display exec->pipe_fds[0]
	display exec->pipe_fds[1]
	display fds[0]
	display fds[1]
end

define a2
	set $z = 0
	while ((*token)[$z].content != (void *)0)
		p (*token)[$z]
		set $z = $z + 1
	end
end

define a3
	set $z = 0
	while (token[$z].content != (void *)0)
		p token[$z]
		set $z = $z + 1
	end
end

define l1
	p get_next_line_bonus(fds[0])
	p sleep(1)
	run
end

define l2
	p get_next_line_bonus(7)
end

define cmd
	set $z1 = 0
	while (exec->commands[$z1] != (void *)0)
		set $z2 = 0
		p $z1
		while (exec->commands[$z1][$z2] != (void *)0)
			p exec->commands[$z1][$z2]
			set $z2 = $z2 + 1
		end
		set $z1 = $z1 + 1
	end
end
