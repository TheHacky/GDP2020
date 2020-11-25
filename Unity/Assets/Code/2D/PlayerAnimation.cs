using System;
using UnityEngine;

namespace Code._2D
{
    [RequireComponent(typeof(Animator), typeof(Rigidbody2D), typeof(PlayerMovement))]
    public class PlayerAnimation : MonoBehaviour
    {
        private Animator _animator = null;
        private Rigidbody2D _rigidbody2D = null;
        private PlayerMovement _playerMovement = null;
        private static readonly int Speed = Animator.StringToHash("Speed");
        private static readonly int IsJumping = Animator.StringToHash("IsJumping");

        private void Awake()
        {
            _animator = GetComponent<Animator>();
            _rigidbody2D = GetComponent<Rigidbody2D>();
            _playerMovement = GetComponent<PlayerMovement>();
        }

        private void Update()
        {
            _animator.SetFloat(Speed, Mathf.Abs(_rigidbody2D.velocity.x));
            _animator.SetBool(IsJumping, !_playerMovement.IsGrounded);
        }
    }
}