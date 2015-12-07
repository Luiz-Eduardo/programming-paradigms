-- phpMyAdmin SQL Dump
-- version 3.3.0
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Dec 07, 2015 at 08:38 AM
-- Server version: 5.5.46
-- PHP Version: 5.5.9-1ubuntu4.14

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `Estoque`
--

-- --------------------------------------------------------

--
-- Table structure for table `employees`
--

CREATE TABLE IF NOT EXISTS `employees` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(60) NOT NULL,
  `age` int(3) NOT NULL,
  `role` int(1) NOT NULL,
  `salary` float NOT NULL,
  `cpf` varchar(20) NOT NULL,
  `email` varchar(45) NOT NULL,
  `address` varchar(200) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=31 ;

--
-- Dumping data for table `employees`
--

INSERT INTO `employees` (`id`, `name`, `age`, `role`, `salary`, `cpf`, `email`, `address`) VALUES
(24, 'HüÚ=z~š$p^ŽÏJ', 19, 2, 129, '11762235420', 'luizeduardob@live.com', 'rua eletricista a'),
(28, '>52Ÿ£ÛÄøU»\\', 18, 2, 200, '11762235420', 'luiz@a.com', 'rua a '),
(29, '÷œˆXÀGAe^''³Aíou˜>ð–ÕÎÑ‡(—©±', 18, 1, 500.2, '11762235420', 'email@dominio.com', 'Rua A'),
(30, '|ç4[ìLJì…ßÒ¼C', 12, 1, 30, '11762235420', 'luiz@alb.com', 'rua a');

-- --------------------------------------------------------

--
-- Table structure for table `products`
--

CREATE TABLE IF NOT EXISTS `products` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(60) NOT NULL,
  `purchaseprice` double NOT NULL,
  `saleprice` double NOT NULL,
  `quantity` int(11) NOT NULL,
  `validity` varchar(15) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=7 ;

--
-- Dumping data for table `products`
--

INSERT INTO `products` (`id`, `name`, `purchaseprice`, `saleprice`, `quantity`, `validity`) VALUES
(1, 'Beterraba', 3, 5, 2, '10/12/2015'),
(2, 'Batata', 2, 5, 50, '10/12/2017'),
(3, 'Banana', 1, 2, 30, '20/10/2019'),
(4, 'Creamcheese', 20, 22, 100, '19/02/2016'),
(5, 'Maca', 2, 5, 10, '31/12/2012'),
(6, 'Pera', 2, 3, 10, '05/09/2019');

-- --------------------------------------------------------

--
-- Table structure for table `users`
--

CREATE TABLE IF NOT EXISTS `users` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `username` varchar(45) NOT NULL,
  `password` char(128) NOT NULL,
  `role` int(1) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=13 ;

--
-- Dumping data for table `users`
--

INSERT INTO `users` (`id`, `username`, `password`, `role`) VALUES
(1, 'admin', 'O', 2),
(5, 'Luiz', '11762235420', 2),
(6, 'asdasd', '11762235420', 1),
(7, 'Ingrid ', '07086218480', 1),
(8, 'Luiz', '11762235420', 2),
(9, 'luiz', '11762235420', 2),
(10, 'Matheus ', '11762235420', 1),
(11, 'asdfa', '11762235420', 1),
(12, 'Matheus ', '11762235420', 1);
