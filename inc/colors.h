/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 10:45:52 by galves-f          #+#    #+#             */
/*   Updated: 2024/04/12 11:54:42 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

# define RST "\033[0m"
# define RED "\033[31m"
# define G "\033[32m"
# define Y "\033[33m"
# define B "\033[34m"
# define M "\033[35m"
# define C "\033[36m"
# define W "\033[37m"

# define RESET_COLOR "\033[0m"
# define BLACK "\033[30m"
# define RED "\033[31m"
# define LIGHT_RED "\033[91m"
# define GREEN "\033[32m"
# define LIGHT_GREEN "\033[92m"
# define YELLOW "\033[33m"
# define LIGHT_YELLOW "\033[93m"
# define BLUE "\033[34m"
# define LIGHT_BLUE "\033[94m"
# define MAGENTA "\033[35m"
# define LIGHT_MAGENTA "\033[95m"
# define CYAN "\033[36m"

# define LIGHT_CYAN "\033[96m"
# define WHITE "\033[37m"
# define GREY "\033[90m"
# define LIGHT_GREY "\033[37m"

# define BLACK_BOLD "\033[1;30m"
# define RED_BOLD "\033[1;31m"
# define GREEN_BOLD "\033[1;32m"
# define YELLOW_BOLD "\033[1;33m"
# define BLUE_BOLD "\033[1;34m"
# define MAGENTA_BOLD "\033[1;35m"
# define CYAN_BOLD "\033[1;36m"
# define WHITE_BOLD "\033[1;37m"

/* top block */
# define TB00 "\n \033[94m╔═════════════════════════════════════════"
# define TB01 "════════════════════════════════════════════════╗\033[0m\n"
/* block bottom */
# define BB00 "\033[94m ╚═══════════════════════════════════════════"
# define BB01 "══════════════════════════════════════════════╝\033[0m\n"
/* row not text */
# define RNT0 "\033[94m ║                                           "
# define RNT1 "                                              ║\033[0m\n"

/* padding before title */
# define PBT0 "\033[94m ║                   \033[0m"
/* padding after title */
# define PAT0 "                     \033[94m║\n\033[0m"

# define TT00 "█▀▀░█▀▀░█░░░█▄█░░░█▀█░█▀▄░█▀▀░█▀▀░█▀▀░█▀█░▀█▀░█▀▀"
# define TT01 "█░░░█░█░█░░░█░█░░░█▀▀░█▀▄░█▀▀░▀▀█░█▀▀░█░█░░█░░▀▀█"
# define TT02 "▀▀▀░▀▀▀░▀▀▀░▀░▀░░░▀░░░▀░▀░▀▀▀░▀▀▀░▀▀▀░▀░▀░░▀░░▀▀▀"

/* padding before text */
# define PBN0 "\033[94m ║     \033[0m"
/* padding after text */
# define PAN0 "     \033[94m║\n\033[0m"

# define PN01 " ██████   ██████  ███              ███         "
# define PN03 "░░██████ ██████  ░░░              ░░░          "
# define PN05 " ░███░█████░███  ████  ████████   ████   █████ "
# define PN07 " ░███░░███ ░███ ░░███ ░░███░░███ ░░███  ███░░  "
# define PN09 " ░███ ░░░  ░███  ░███  ░███ ░███  ░███ ░░█████ "
# define PN11 " ░███      ░███  ░███  ░███ ░███  ░███  ░░░░███"
# define PN13 " █████     █████ █████ ████ █████ █████ ██████ "
# define PN15 "░░░░░     ░░░░░ ░░░░░ ░░░░ ░░░░░ ░░░░░ ░░░░░░  "
# define PN02 " █████               ████  ████ "
# define PN04 "░░███               ░░███ ░░███ "
# define PN06 " ░███████    ██████  ░███  ░███ "
# define PN08 " ░███░░███  ███░░███ ░███  ░███ "
# define PN10 " ░███ ░███ ░███████  ░███  ░███ "
# define PN12 " ░███ ░███ ░███░░░   ░███  ░███ "
# define PN14 " ████ █████░░██████  █████ █████"
# define PN16 "░░░░ ░░░░░  ░░░░░░  ░░░░░ ░░░░░ "

#endif
